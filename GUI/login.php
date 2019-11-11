<?php
require_once("system.php");

if (!session_start()) die("SESSIONINITFAILED");

if (($_POST["action"] ?? "") == "logout") {
	$_SESSION["login"] = false;
	if (!session_destroy()) die("SESSIONDESTROYFAILED");
	die("LOGOUT SUCCESSFUL!");
}

if (($_POST["action"] ?? "") == "login") {
	//TODO: check username and password
	$_SESSION["login"] = true;
	header("Location: main.php");
	die();
}

if (sessionvalid()) {
	header("Location: main.php");
	die();
}

?>

<html>
	<head>
		<title>ProjectSpyder Login</title>
		<style>
			body {
				background-color: #00000000;
			}
		</style>
		<script>
			/*
			//add post login routine if needed
			async function login() {
			}
			*/
		</script>
	</head>
	<body>
		<div id=logindiv>
			<form action="login.php" method="post" onsubmit="">
				<input type=text name=username placeholder="Username">
				<input type=password name=password placeholder="Password">
				<input type=text name=action value=login style="display: none;" > 
				<input type=submit name=login value=LOGIN>
			</form>
		</div>
	</body>
</html>