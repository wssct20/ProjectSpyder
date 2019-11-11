<?php 
//this is the main screen of the gui

require_once("system.php");

if (!session_start()) die("SESSIONINITFAILED");

//switch to login page if session is invalid
if (!sessionvalid()) {
	header("Location: login.php");
	die();
}

?>


<html>
	<head>
		<title>ProjectSpyder GUI</title>
		<style>
			body {
				background-color: black;
			}
			h1 {
				color: white;
			}
			input {
			    color: white;
			    background-color: black;
			}
		</style>
		<script>
			//to be added
		</script>
	</head>
	<body>
		<h1>ProjectSpyder</h1>
		<form action="login.php" method=post>
			<input type=text name=action value=logout style="display: none;">
			<input type=submit name=submit value=Logout>
		</form>
		<iframe id=mainframe style="display: none;" />
	</body>
<html>