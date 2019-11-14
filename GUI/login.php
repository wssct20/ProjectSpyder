<?php
require_once("system.php");
global $systemname;

$action = $_POST["action"] ?? "";
switch ($action) {
	case "login":
		//Login
		if (sizeof(getusers()) == 0) {
			header("DEBUG: login.php login because of no users successful");
			$_SESSION["login"] = true;
			header("Location: main.php",true,303);
			die();
		}
		$inputusername = $_POST["username"];
		$inputpassword = $_POST["password"];
		$user = getuserbyusername($username);
		if (sizeof($user) == 0) loginfailed();
		if (calculateuserhash($username, $password) != $user["pass"]) loginfailed();
		$_SESSION["login"] = true;
		header("DEBUG: login.php userlogin successful");
		header("Location: main.php",true,303);
		die();
		//break;
	case "logout":
		//Logout
		header("DEBUG: login.php logout");
		$_SESSION["login"] = false;
		if (!session_destroy()) die("SESSIONDESTROYFAILED");
		header("Location: login.php",true,303);
		die();
		//break;
	default:
		//unrecognized action
	case "":
		//no action specified
		//break;
}

if (sessionvalid()) {
	header("DEBUG: login.php session valid, redirect to main");
	header("Location: main.php",true,307);
	die();
}

function loginfailed() {
	header("DEBUG: login.php login failed");
	header("Location: login.php",true,303);
	die();
}

?>

<html>
	<head>
		<title><?php echo $systemname;?> Login</title>
		<style type="text/css">
			body {
				background-color: black;
			}
			input {
			    color: white;
			    background-color: black;
			}
			h1 {
				color: white;
			}
			#logindiv {
				text-align: center;
			}
		</style>
	</head>
	<body>
		<div id=logindiv>
			<h1><?php echo $systemname;?> Login</h1>
			<form action="login.php" method="post" onsubmit="">
				<input type=text name=username placeholder="Username"><br>
				<input type=password name=password placeholder="Password"><br>
				<input type=text name=action value=login style="display: none;"> 
				<input type=submit name=login value=LOGIN>
			</form>
		</div>
	</body>
</html>