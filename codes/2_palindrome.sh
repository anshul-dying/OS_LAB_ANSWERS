echo -n "Enter a String to check: "
read s

rev=$(echo "$s" | rev)

if [ "$s" = "$rev" ]; then
	echo "Palindrome"
else
	echo "Not Palindrome"
fi
