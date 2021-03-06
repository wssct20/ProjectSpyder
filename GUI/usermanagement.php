<?php
require_once("system.php");
checksession();

$action = $_POST["action"] ?? "";

if ($action == "create") {
	//create user
	$username = $_POST["username"] ?? "";
	$password = $_POST["password"] ?? "";
	$role = $_POST["role"] ?? "";
	$role = "admin"; //TODO: configure role management
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
	header("Location: usermanagement.php",true,303);
	die();
}

if ($action == "delete") {
	//delete user
	$username = $_POST["username"] ?? "";
	if ($username == "") die("INVALIDUSERNAME");
	$user = getuserbyusername($username);
	deleteuser($user["id"], $user["name"]);
	header("DEBUG: usermanagement.php delete user successful");
	header("Location: usermanagement.php",true,303);
	die();
}

?>

<!DOCTYPE html>
<html lang="de">
	<head>
        <meta charset="utf-8">
        <link rel="stylesheet" href="style.css">
        <link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
        <link href="https://fonts.googleapis.com/css?family=Roboto+Condensed&display=swap" rel="stylesheet"> 
		<title><?php echo $systemname;?> Usermanagement</title>
		<style>
			td {
				color: white;
			}
			th {
				color: white;
				border-bottom: white solid 1px;
			}
			input {
			    color: white;
			    background-color: black;
			}
			label {
				color: white;
			}
		</style>
	</head>
	<body>
		<nav>
			<h1><a href="main.php"><?php echo $systemname;?></a> Usermanagement</h1>
			<ul>
                <div class="separator"></div>
				<li><a href="main.php">Home</a></li>
			</ul>
		</nav>
		
		<div class="settings">
			
			<h3>User List</h3>
			<?php 
			$users = getusers();
			if (sizeof($users) == 0) {
				echo "No users found.";
			} else {
				?>
				<table>
					<?php 
					echo "<tr>";
					echo "<th>" . "ID" . "</th>";
					echo "<th>" . "Username" . "</th>";
					echo "<th>" . "Role" . "</th>";
					echo "<th>" . "" . "</th>"; //line with delete button
					echo "</tr>";
					foreach ($users as $user) {
						echo "<tr>";
						echo "<td>" . $user["id"] . "</td>";
						echo "<td>" . $user["role"] . "</td>";
						?>
						echo "<td>" . sanitizehtml($user["name"]) . "</td>";
						<td>
							<form method=post style="margin: 0;">
								<input type=text name=username value="<?php echo $user["name"]; ?>" style="display: none;">
								<input type=text name=action value=delete style="display: none;">
								<input type=submit name=submit value="Delete">
							</form>
						</td>
						<?php
						echo "</tr>";
					}
					?>
				</table>
				<?php 
			}
			?>
			
			<h3>Create User</h3>
			<form method="post">
				<input type=text name=username placeholder="Username"><br>
				<input type=password name=password placeholder="Password"><br>
				<div style="display: none;">
				<input type="radio" id="admin" name="role" value="admin">
			    <label for="admin"> Admin</label><br>
			    <!-- TODO: configure role management
			    <input type="radio" id="user" name="role" value="user">
			    <label for="user"> User</label><br>
			    <input type="radio" id="guest" name="role" value="guest">
			    <label for="guest"> Guest</label><br>
			    -->
			    </div>
				<input type=text name=action value=create style="display: none;">
				<input type=submit value="Create User">
			</form>
			
		</div>
	</body>
</html>