#!/usr/bin/env bash
# Automated end-to-end tests: feed scripted keystrokes to the program and
# check the output. Run from the project root:  make test
#
# Each test starts from its own temporary data file.

BIN="./contacts"
PASS=0
FAIL=0
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

# run_case "<description>" "<seed file content>" "<input lines>" "<expected text>" ["<unexpected text>"]
run_case() {
    local desc="$1" seed="$2" input="$3" expect="$4" reject="${5:-}"
    local file="$TMP/data.txt"
    printf "%s" "$seed" > "$file"

    local output
    output="$(printf "%b" "$input" | "$BIN" "$file" 2>&1)"

    if [[ "$output" == *"$expect"* ]] && { [[ -z "$reject" ]] || [[ "$output" != *"$reject"* ]]; }; then
        echo "PASS  $desc"
        PASS=$((PASS + 1))
    else
        echo "FAIL  $desc"
        echo "      expected: $expect"
        [[ -n "$reject" ]] && echo "      must not contain: $reject"
        FAIL=$((FAIL + 1))
    fi
}

SEED=$'Abel Tesfay|+251911000101|abel@example.com\nZed Zeru|+251922000202|\nMaya Mesfin|+251933000303|\n'

# ---- Add -----------------------------------------------------------------
run_case "add contact" "" "1\nAbel\n0911000101\nabel@x.com\n0\n" "Contact added: Abel (+251911000101)"
run_case "local 09 number is normalized" "" "1\nAbel\n0911000101\n\n6\n0\n" "+251911000101"
run_case "duplicate number rejected" "$SEED" "1\nOther Person\n0911000101\n\n0\n" "already belongs to Abel Tesfay"
run_case "invalid number rejected" "" "1\nAbel\nabc\n\n0\n" "may only contain digits"
run_case "too-short number rejected" "" "1\nAbel\n12345\n\n0\n" "between 7 and 15 digits"
run_case "invalid email rejected" "" "1\nAbel\n0911000101\nnot-an-email\n\n0\n" "Email must look like"
run_case "empty name cancels" "" "1\n\n0\n" "Cancelled."
run_case "name with | rejected" "" "1\nA|B\n\n0\n" "cannot contain the '|'"

# ---- Sorted order --------------------------------------------------------
run_case "list is sorted by name" "$SEED" "6\n0\n" "Abel Tesfay"
# Row order check: Abel must appear before Maya, and Maya before Zed.
printf "%s" "$SEED" > "$TMP/s.txt"
sorted_out="$(printf "6\n0\n" | "$BIN" "$TMP/s.txt")"
a=$(echo "$sorted_out" | grep -n "Abel Tesfay  " | head -1 | cut -d: -f1)
m=$(echo "$sorted_out" | grep -n "Maya Mesfin  " | head -1 | cut -d: -f1)
z=$(echo "$sorted_out" | grep -n "Zed Zeru  " | head -1 | cut -d: -f1)
if [[ -n "$a" && -n "$m" && -n "$z" && "$a" -lt "$m" && "$m" -lt "$z" ]]; then
    echo "PASS  rows appear in A-M-Z order"; PASS=$((PASS + 1))
else
    echo "FAIL  rows appear in A-M-Z order"; FAIL=$((FAIL + 1))
fi
run_case "new contact inserted in sorted position" "$SEED" "1\nBeth\n0944000404\n\n6\n0\n" "Total: 4 contact(s)"

# ---- Search --------------------------------------------------------------
run_case "search by partial name (case-insensitive)" "$SEED" "4\nmAyA\n0\n" "1 contact(s) found"
run_case "search by name - not found" "$SEED" "4\nnobody\n0\n" "No contact found"
run_case "search by number" "$SEED" "5\n0922000202\n0\n" "Zed Zeru"
run_case "search by number - not found" "$SEED" "5\n0900000000\n0\n" "No contact with the number"

# ---- Count ---------------------------------------------------------------
run_case "count contacts" "$SEED" "7\n0\n" "Number of contacts: 3"

# ---- Delete --------------------------------------------------------------
run_case "delete by name" "$SEED" "2\nZed\ny\n7\n0\n" "Number of contacts: 2"
run_case "delete by number" "$SEED" "2\n0911000101\ny\n7\n0\n" "Number of contacts: 2"
run_case "delete cancelled with n" "$SEED" "2\nZed\nn\n7\n0\n" "Number of contacts: 3"
run_case "delete unknown contact" "$SEED" "2\nnobody\n0\n" "No contact found"

# ---- Update --------------------------------------------------------------
run_case "update name keeps order" "$SEED" "3\nZed\nAaron Zeru\n\n\n6\n0\n" "Contact updated."
run_case "update to existing number rejected" "$SEED" "3\nZed\n\n0911000101\n\n0\n" "already belongs to Abel Tesfay"
run_case "update clears email with -" "$SEED" "3\nAbel\n\n\n-\n6\n0\n" "Contact updated."

# ---- Undo (stack) --------------------------------------------------------
run_case "undo add" "$SEED" "1\nNew One\n0955000505\n\n8\n7\n0\n" "Number of contacts: 3"
run_case "undo delete restores contact" "$SEED" "2\nZed\ny\n8\n7\n0\n" "Number of contacts: 3"
run_case "undo update restores old name" "$SEED" "3\nZed\nQuincy\n\n\n8\n6\n0\n" "Zed Zeru" "Quincy  "
run_case "undo with nothing to undo" "" "8\n0\n" "Nothing to undo."
run_case "undo is LIFO (two deletes, two undos)" "$SEED" "2\nZed\ny\n2\nMaya\ny\n8\n8\n7\n0\n" "Number of contacts: 3"

# ---- Activity queue ------------------------------------------------------
run_case "activity log records add" "" "1\nAbel\n0911000101\n\n9\n0\n" "Added Abel"
many=""
for i in 1 2 3 4 5 6 7 8 9 10 11 12; do
    many+="1\nPerson$i\n09110001$(printf %02d $i)\n\n"
done
run_case "activity queue keeps only the last 10" "" "${many}9\n0\n" "Added Person12" "Added Person1]"
run_case "activity queue drops oldest entries" "" "${many}9\n0\n" "Added Person3" "Added Person2"

# ---- Menu / input handling -----------------------------------------------
run_case "invalid menu option" "" "x\n0\n" "Invalid option"
run_case "end of input exits and saves" "" "1\nAbel\n0911000101\n\n" "saved to"

# ---- File I/O ------------------------------------------------------------
run_case "loads contacts from file" "$SEED" "7\n0\n" "Loaded 3 contact(s)"
run_case "skips bad and duplicate lines" $'Good One|+251911000101|\nbroken line\nDup|+251911000101|\n' "0\n" "2 invalid or duplicate line(s) skipped"

# persistence across two runs of the program
printf "" > "$TMP/persist.txt"
printf "1\nPersisted Pat\n0911000999\n\n0\n" | "$BIN" "$TMP/persist.txt" > /dev/null
second="$(printf "4\npersisted\n0\n" | "$BIN" "$TMP/persist.txt")"
if [[ "$second" == *"Persisted Pat"* ]]; then
    echo "PASS  data survives a restart"; PASS=$((PASS + 1))
else
    echo "FAIL  data survives a restart"; FAIL=$((FAIL + 1))
fi

# deleted contact must not come back after a restart
printf "2\nPersisted\ny\n0\n" | "$BIN" "$TMP/persist.txt" > /dev/null
third="$(printf "7\n0\n" | "$BIN" "$TMP/persist.txt")"
if [[ "$third" == *"Number of contacts: 0"* ]]; then
    echo "PASS  deletion survives a restart"; PASS=$((PASS + 1))
else
    echo "FAIL  deletion survives a restart"; FAIL=$((FAIL + 1))
fi

echo
echo "Passed: $PASS   Failed: $FAIL"
[[ "$FAIL" -eq 0 ]]
