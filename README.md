# archi_lab5


task0:

**	execv - execute with the full path example: /bin/ls 
**	exevp - execute with both options- with path and without.
**	execv - close the program besause the command open a new frame and kill the 
	previous prosses, and run only the new one.
**	execv and execvp do not recognize the library '*'


---------------------------------------------------------------
task1a:
**	adding cpid' if cpid==0 -> you're "the main", else-> you're a child -> execute the cmd_line
**	free_line -> didn't touch it because of there was no need at this point

---------------------------------------------------------------
task 1b:
**	check the condition for wait -> if cmd_line.blocking==1 ->should wait
**	cmd_line.blocking : a field of the struct that flag if the last char of input == &
**	waitpid(a,b,c) : a=is the cpid (to check if I'm the father/son , b=?? , c=open the option of wait

---------------------------------------------------------------

task 1c:
** 	adding input and output stream options
**	the filed line->output_redirect and line->input_redirect are initial during the
	cmd_line *line = parse_cmd_lines(s);
	if they are != NULL ->there is a notation for input/output streaming.
**	close(a) ->need to close the streaming to a,
	a is a adress of streaming.


---------------------------------------------------------------

task 2:
**	fork= copy the current frame(from this exact point), open the copy (=of the child1), and run the child1 frame.
** 	if(child1) ->   1) close the output-stream
			2) connect to the pipe
			3) do the execvp command (note: the "ls -l" command's output is in the pipe.
**	#4 close the pipe input of child1 and father
**	fork= copy the current frame (from this exact point), open the copy (=of the child2), and run the child2 frame.
** 	if(child2) ->   1) close the input-stream
			2) connect to the pipe
			3) do the execvp command (note: the "tail -n 2" command's output is in the pipe.
**	#7 close the pipe input -> the input and output are closed ->the pipe is closed.
** 	#8 command to the father to wait before closing the program forchild1 and child2 to finish their own frames runnings

---------------------------------------------------------------

task3:

**	pipes input: when initial cmd_line *line with pipes saperate
		cat < 1.txt|wc -l>out1  [example]
		the constructor will make 2 lines:
		1st: line-> input_redirect = 1.txt , arguments[0] = cat , line.next = 2nd
		2nd: line-> output_direct = out1 , argument[0]=wc,argument[1]= -l
**	the pipeExecute func get the 1st line, coppy-paste to task 2, change only the execvp line command 
	(send saperately 1st and 2nd to the exec


