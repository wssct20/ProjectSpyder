<?php
require_once("system.php");
checksession();

$action = $_POST["action"] ?? "";

if ($action == "create") {
	//create user
	$username = $_POST["username"] ?? "";
	$password = $_POST["password"] ?? "";
	$role = $_POST["role"] ?? "";
	if ($username == "" || $password == "" || $role == "") die("CREDENTIALSINCOMPLETE");
	$allusers = getusers();
	foreach ($allusers as $user) {
		if ($user["name"] == $username) {
			die("USERNAMEALREADYEXISTS");
		}
	}
	$password = calculateuserhash($username, $password);
	adduser($username, $password, $role);
	header("DEBUG: usermanagement.php create user successful");
	header("Location: usermanagement.php",true,302);
	die();
}

if ($action == "delete") {
	//delete user
	$username = $_POST["username"] ?? "";
	if ($username == "") die("INVALIDUSERNAME");
	$user = getuserbyusername($username);
	deleteuser($user["id"], $user["name"]);
	header("DEBUG: usermanagement.php delete user successful");
	header("Location: usermanagement.php",true,302);
	die();
}

?>

<html>
	<head>
		<title><?php echo $systemname;?> Usermanagement</title>
		<style>
			body {
				background-color: black;
			}
			h1 {
				color: white;
			}
			h3 {
				color: white;
			}
			td {
				color: white;
			}
			th {
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
			label {
				color: white;
			}
		</style>
	</head>
	<body>
		<nav>
			<h1><?php echo $systemname;?> Usermanagement</h1>
			<ul>
				<li><a href="main.php">Home</a></li>
			</ul>
		</nav>
		<h3>User List</h3>
		<table>
			<?php 
			$users = getusers();
			if (sizeof($users) == 0) {
				echo "Error: No users found.";
			}
			echo "<tr>";
			echo "<th>" . "ID" . "</th>";
			echo "<th>" . "Username" . "</th>";
			echo "<th>" . "" . "</th>"; //line with delete button
			echo "</tr>";
			foreach ($users as $user) {
				echo "<tr>";
				echo "<td>" . $user["id"] . "</td>";
				echo "<td>" . $user["name"] . "</td>";
				?>
				<form method=post>
					<input type=text name=username value="<?php echo $user["name"];?>" style="display: none;">
					<input type=text name=action value=delete style="display: none;">
					<input type=submit name=submit value="Delete">
				</form>
				<?php
				echo "</tr>";
			}
			?>
		</table>
		<h3>Create User</h3>
		<form method="post">
			<input type=text name=username placeholder="Username"><br>
			<input type=password name=password placeholder="Password"><br>
			<input type="radio" id="admin" name="role" value="admin">
		    <label for="admin"> Admin</label><br>
		    <input type="radio" id="user" name="role" value="user">
		    <label for="user"> User</label><br>
		    <input type="radio" id="guest" name="role" value="guest">
		    <label for="guest"> Guest</label><br>
			<input type=text name=action value=create style="display: none;">
			<input type=submit value="Create User">
		</form>
	</body>
</html>