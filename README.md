# archi_lab5


task0:</br></br>

**	execv - execute with the full path example: /bin/ls </br>
**	exevp - execute with both options- with path and without.</br>
**	execv - close the program besause the command open a new frame and kill the </br>
	previous prosses, and run only the new one.</br>
**	execv and execvp do not recognize the library '*'</br>


---------------------------------------------------------------
task1a:</br>
**	adding cpid' if cpid==0 -> you're "the main", else-> you're a child -> execute the cmd_line</br>
**	free_line -> didn't touch it because of there was no need at this point</br>

---------------------------------------------------------------
task 1b:
**	check the condition for wait -> if cmd_line.blocking==1 ->should wait</br>
**	cmd_line.blocking : a field of the struct that flag if the last char of input == &</br>
**	waitpid(a,b,c) : a=is the cpid (to check if I'm the father/son , b=?? , c=open the option of wait</br></br>

---------------------------------------------------------------

task 1c:</br>
** 	adding input and output stream options</br>
**	the filed line->output_redirect and line->input_redirect are initial during the</br>
	cmd_line *line = parse_cmd_lines(s);</br>
	if they are != NULL ->there is a notation for input/output streaming.</br>
**	close(a) ->need to close the streaming to a,</br>
	a is a adress of streaming.</br></br>


---------------------------------------------------------------

task 2:</br>
**	fork= copy the current frame(from this exact point), open the copy (=of the child1), and run the child1 frame.</br>
** 	if(child1) -> </br>  1) close the output-stream</br>
			2) connect to the pipe
			3) do the execvp command (note: the "ls -l" command's output is in the pipe.</br>
**	#4 close the pipe input of child1 and father</br>
**	fork= copy the current frame (from this exact point), open the copy (=of the child2), and run the child2 frame.</br>
** 	if(child2) ->   </br>1) close the input-stream</br>
			2) connect to the pipe</br>
			3) do the execvp command (note: the "tail -n 2" command's output is in the pipe.</br>
**	#7 close the pipe input -> the input and output are closed ->the pipe is closed.</br>
** 	#8 command to the father to wait before closing the program forchild1 and child2 to finish their own frames runnings</br></br>

---------------------------------------------------------------

task3:</br>

**	pipes input: when initial cmd_line *line with pipes saperate</br>
		cat < 1.txt|wc -l>out1  [example]</br>
		the constructor will make 2 lines:</br>
		1st: line-> input_redirect = 1.txt , arguments[0] = cat , line.next = 2nd</br>
		2nd: line-> output_direct = out1 , argument[0]=wc,argument[1]= -l</br>
**	the pipeExecute func get the 1st line, coppy-paste to task 2, change only the execvp line command </br>
	(send saperately 1st and 2nd to the exec</br>


