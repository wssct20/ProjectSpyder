<?php 
//this is the main screen of the gui

require_once("system.php");
global $systemname;

checksession();

?>


<html>
	<head>
		<title><?php echo $systemname;?> GUI</title>
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
			
			nav {
				color: white;
			}
			a {
				color: white;
			}
		</style>
		<script>
			//to be added
		</script>
	</head>
	<body>
		<nav>
			<h1>ProjectSpyder</h1>
			<ul>
				<li><a href="main.php">Home</a></li>
				<li><a href="devices.php">Devices</a></li>
			</ul>
		</nav>
		<form action="login.php" method=post>
			<input type=text name=action value=logout style="display: none;">
			<input type=submit name=submit value=Logout>
		</form>
		<iframe id=mainframe style="display: none;" />
	</body>
<html>