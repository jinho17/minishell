# MINISHELL-TESTER

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# Compile and set executable rights
make -C ../ > /dev/null
cp ../minishell .
chmod 755 minishell

function exec_test()
{
	TEST1=$(echo $@ "; exit" | ./minishell 2>&-)
	ES_1=$?
	TEST2=$(echo $@ "; exit" | bash 2>&-)
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	echo
	echo
	sleep 0.1
}

printf "$BOLDMAGENTA __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo

#absolute path
exec_test '/bin/ls'
exec_test '/bin/echo'
exec_test '/bin/ls -al'
exec_test '/bin/echo 123'

#echo
exec_test 'echo'
exec_test 'echo test tout'
exec_test 'echo test      tout'
exec_test 'echo -n test tout'
exec_test 'echo -n -n -n test tout'

#exit
exec_test 'exit'
# exit 42

#$?
exec_test '/bin/ls; echo $?'
exec_test '/bin/ls asdfasdf; echo $?'
# cd asdf; echo $?
# export TE+S=T=""; echo $?

#semicolon
exec_test '/bin/ls;/bin/echo'
exec_test '   /bin/ls     ;      /bin/echo     '
exec_test '/bin/echo 1; /bin/echo    test   ; /bin/echo   abc'
# ;; test

#double quote
exec_test '/bin/ls "-al"'
exec_test 'echo ""'
exec_test 'echo "$"'
exec_test 'echo "test1; test2;"'
exec_test 'echo "test1; test2" "; test3"'

#env & export
exec_test 'export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST'
exec_test 'export TEST=LOL ; echo $TEST'
# env
# export
# export z=1; env
# export "test=1"; env
# export "hello="; env
# export TES=T=""; env
# export TEST="ls       -l     - a" ; echo $TEST

#unset
# unset z; env
# unset 'hello'; env

#error
# export 1TEST
# export =
# export ""=""
# export TE+S=T=""
# export TEST=LOL; export TEST+=LOL ; echo $TEST ;
# unset
# unset "test="
# unset "test=1"

#environment variable $
exec_test 'echo $USER'
exec_test 'echo $'
exec_test 'echo "$1TEST"'
exec_test 'echo "$USER" $USER'
exec_test 'echo "$TEST$TEST$TEST"'
exec_test 'echo "$TEST$TEST=lol$TEST"'
exec_test 'echo "   $TEST lol $TEST"'
exec_test 'echo $TEST$TEST$TEST'
exec_test 'echo    $TEST lol $TEST'
exec_test 'echo $TEST $TEST'
exec_test 'echo "$T1TEST"'

#cd, pwd
exec_test 'cd /Users ; pwd'
exec_test 'cd ; pwd'
# cd .. ; pwd
# cd .; pwd
# cd asdf

#relative path
exec_test 'cd /; ./bin/ls'
exec_test 'cd /bin; ./ls'

#without path
exec_test 'ls'
exec_test 'echo'
# unset PATH; echo $PATH;
# ls;
# export PATH=/bin:/usr/sbin; echo $PATH;
# ls;

#simple quote
exec_test "echo 'test1' 'test2'"
exec_test "echo 'test1 ' 'test2  '"
exec_test "echo '   ;; ; test'   "
exec_test "echo '$USER $TEST'"

#redirect
exec_test 'echo test > ls ; cat ls'
exec_test 'cat < ls'
exec_test 'cat < ls > ls'
exec_test '> lol echo test lol; cat lol'
exec_test '>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test'
# echo test > ls >> ls >> ls ; echo test >> ls; cat ls
# echo abc > test >> ls; cat test; cat ls
# <
# <<<
# >>>

#pipe
exec_test 'ls|ls|ls|ls|ls|ls|ls'
exec_test 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e'
exec_test 'cat /dev/random | head -c 100 | wc -c'
exec_test 'cat Makefile | grep NAME | more'
exec_test 'cat Makefile | grep NAME | cat -e'
exec_test 'cat Makefile | grep arcu | cat -e'
# echo testing multi ; echo "test 1 ; | and 2" ; cat Makefile | grep NAME
# cat test | grep def
# ls -la | wtf
# | test

#pipe + redirect
exec_test 'echo 123 | cat | cat -e > test; cat test'
# echo abc | cat | cat -e >> test; cat test
# cat < test | echo abc >> test; cat test

rm lol ls test
