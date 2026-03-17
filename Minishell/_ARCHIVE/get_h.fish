function list_declarations2
	if test (count $argv) -eq 0
		echo "Usage: list_declarations file1.c file2.c ..."
		return 1
	end

	for file in $argv
		# Capture the output into a list variable named 'output'
		set -l output (command awk '/^[ \t]*(static[ \t]+)?(t_plist|t_list|void|int|size_t|char|long|long long|t_env|t_shell|t_token|t_command|t_node)[ \t]+\**[a-zA-Z_][a-zA-Z0-9_]*[ \t]*\(/ { print $0 ";" }' $file | tr -d '\r')
		# set -l output (command awk '/^[ \t]*([ \t]+)?(t_plist|t_list|void|int|size_t|char|long|long long|t_env|t_shell|t_token|t_command|t_node)[ \t]+\**[a-zA-Z_][a-zA-Z0-9_]*[ \t]*\(/ { print $0 ";" }' $file | tr -d '\r')
		
		# Count the number of elements in the list
		set -l func_count (count $output)

		# Print the header with the file name and the count
		echo -e "\n// $file N: $func_count"

		# Print each function line
		for line in $output
			echo $line
		end
	end
end

function list_decl_bulk2
	if test (count $argv) -gt 0 -a -d $argv[1]
		# If a directory was passed, search inside it
		for i in $argv[1]/*.c
			list_declarations2 $i
		end
	else
		# No directory passed, use current dir
		for i in *.c
			list_declarations2 $i
		end
	end
end

begin 
echo ""
echo "// -----------------------------------------------------------------------------"
echo "// FUNCTION PROTOTYPES"
echo "// -----------------------------------------------------------------------------"
list_decl_bulk2 src/
echo ""
echo "// -----------------------------------------------------------------------------"
echo "// BUILTIN PROTOTYPES"
echo "// -----------------------------------------------------------------------------"
list_decl_bulk2 src/builtins/
# end
# end | wl-copy
end | xsel -b
