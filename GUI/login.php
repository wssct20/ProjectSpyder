<?php
require_once("system.php");

if (!session_start()) die("SESSIONINITFAILED");
checksession();

if ($_POST["action"] ?? "" == "logout") {
	if (!session_destroy()) die("LOGOUT FAILED!");
	die("LOGOUT SUCCESSFUL");
}

if ($_POST["action"] ?? "" == "login") {
	//check username and password
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
			async function login() {
				//add post login routine
			}
		</script>
	</head>
	<body>
		<div id=logindiv>
			<form action="javascript:void(0)" onsubmit="login();">
				<input type=text id=username placeholder="Username">
				<input type=password id=password placeholder="Password">
				<input type=submit>
			</form>
		</div>
	</body>
</html>