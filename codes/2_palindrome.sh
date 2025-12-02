echo -n "Enter a String to check: "
read s

clear=$(echo "$s" | tr -d ' ')
rev=$(echo "$clear" | rev)

if [ "$clear" = "$rev" ]; then
	echo "Palindrome"
else
	echo "Not Palindrome"
fi
