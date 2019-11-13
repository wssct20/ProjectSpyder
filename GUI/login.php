<?php
require_once("system.php");
global $systemname;

$action = $_POST["action"] ?? "";
switch ($action) {
	case "login":
		//Login
		//TODO: check username and password
		$_SESSION["login"] = true;
		header("Location: main.php",true,307);
		die();
		//break;
	case "logout":
		//Logout
		$_SESSION["login"] = false;
		if (!session_destroy()) die("SESSIONDESTROYFAILED");
		header("Location: login.php",true,302);
		die();
		//break;
	default:
		//unrecognized action
	case "":
		//no action specified
		//break;
}

if (sessionvalid()) {
	header("Location: main.php",true,307);
	die();
}

?>

<html>
	<head>
		<title><?php echo $systemname;?> Login</title>
		<style>
			body {
				background-color: black;
			}
			input {
			    color: white;
			    background-color: black;
			}
		</style>
		<script>
			/*
			//TODO: add post login routine if needed
			async function login() {
			}
			*/
		</script>
	</head>
	<body>
		<div id=logindiv>
			<h1><?php echo $systemname;?> Login</h1>
			<form action="login.php" method="post" onsubmit="">
				<input type=text name=username placeholder="Username">
				<input type=password name=password placeholder="Password">
				<input type=text name=action value=login style="display: none;" > 
				<input type=submit name=login value=LOGIN>
			</form>
		</div>
	</body>
</html>