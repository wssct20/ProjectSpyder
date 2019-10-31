<?php
die("GUIUNFINISHED");
//TODO whole gui stuff is untested

require_once("GUI/system.php");

if (!session_start()) die("SESSIONINITFAILED");
//sessionvalid(); //somehow switch to login page if session is invalid

?>

<html>
	<head>
		<title>ProjectSpyder GUI</title>
		<style>
			body {
				background-color: black;
			}
		</style>
		<script>
			//to be added
		</script>
	</head>
	<body>
		<iframe id=mainframe />
	</body>
<html>