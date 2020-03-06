<?php
require_once("system.php");
global $systemname;
checksession();

$action = $_POST["action"] ?? "";

if ($action == "details") {
    //TODO: add details config
    header("Location: conditions.php",true,303);
}

?>

<!DOCTYPE html>
<html lang="de">
	<head>
        <meta charset="utf-8">
        <link rel="stylesheet" href="style.css">
        <link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
        <link href="https://fonts.googleapis.com/css?family=Roboto+Condensed&display=swap" rel="stylesheet"> 
		<title><?php echo $systemname;?> Devices</title>
		<style>
			td {
				color: white;
			}
			th {
				color: white;
				border-bottom: white solid 1px;
			}
		</style>
	</head>
	<body>
		<nav>
			<h1><a href="main.php"><?php echo $systemname;?></a> Conditions</h1>
			<ul>
                <div class="separator"></div>
				<li><a href="main.php">Home</a></li>
				<!--<li><a href="conditions.php">Conditions</a></li>-->
			</ul>
		</nav>
		
		<div class="settings">
		
			<h2>Conditions</h2>
			<?php 
			//this generates a table of conditons
			$conditions = getconditions();
			if (sizeof($conditions) == 0) {
				echo("No conditions found.");
			} else {
				?>
				<table>
					<?php
					echo "<tr>";
                    echo "<th>" . "ID" . "</th>";
                    echo "<th>" . "Name" . "</th>";
					echo "<th>" . "IF ID" . "</th>";
					echo "<th>" . "IF Variable" . "</th>";
					echo "<th>" . "IF Value" . "</th>";
					echo "<th>" . "THEN ID" . "</th>";
					echo "<th>" . "THEN Variable" . "</th>";
					echo "<th>" . "THEN Value" . "</th>";
					echo "<th>" . "" . "</th>"; //line with manage button
					echo "</tr>";
					foreach ($conditions as $condition) {
						echo "<tr>";
						echo "<td>" . $condition["id"] . "</td>";
						echo "<td>" . $condition["name"] . "</td>";
						echo "<td>" . $condition["ifid"] . "</td>";
						echo "<td>" . $condition["ifvar"] . "</td>";
						echo "<td>" . $condition["ifvalue"] . "</td>";
						echo "<td>" . $condition["thenid"] . "</td>";
						echo "<td>" . $condition["thenvar"] . "</td>";
						echo "<td>" . $condition["thenvalue"] . "</td>";
						?>
						<td>
							<form method=post style="margin: 0;">
								<input type=text name=id value="<?php echo $condition["id"]; ?>" style="display: none;">
								<input type=text name=action value=details style="display: none;">
								<input type=submit name=submit value="Manage">
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
			
		</div>
	</body>
</html>
