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
				text-color: white;
			}
		</style>
		<script>
			//to be added
		</script>
	</head>
	<body>
		<h1>ProjectSpyder</h1>
		<iframe id=mainframe />
	</body>
<html>