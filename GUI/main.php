<?php 
//this is the main screen of the gui

require_once("system.php");
global $systemname;

checksession();

?>

<!DOCTYPE html>
<html lang="de">
	<head>
        <meta charset="utf-8">
		<title><?php echo $systemname;?> GUI</title>
        <link rel="stylesheet" href="style.css">
        <link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
        <link href="https://fonts.googleapis.com/css?family=Roboto+Condensed&display=swap" rel="stylesheet"> 
		<style>
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
		<nav>
			<h1>ProjectSpyder</h1>
			<ul>
				<!--<li><a href="main.php">Home</a></li>-->
				<li><a href="devices.php">Devices</a></li>
				<li><a href="usermanagement.php">Usermanagement</a></li>
			</ul>
			<ul>
				<li class="bordered">
					<form action="login.php" method=post>
						<input type=text name=action value=logout style="display: none;">
						<input type=submit name=submit value=Logout>
					</form>
				</li>
			</ul>
		</nav>
		
		<iframe id=mainframe style="display: none;" />
	</body>
<html>