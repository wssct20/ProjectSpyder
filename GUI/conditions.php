<?php
require_once("system.php");
global $systemname;
checksession();

$action = $_POST["action"] ?? "";

if ($action == "create") {
	//TODO: check for user permission
	//TODO: untested code
	$ifid = $_POST["ifid"] ?? die("INVALIDIFID");
	$ifvar = $_POST["ifvar"] ?? die("INVALIDIFVAR");
	$ifvalue = $_POST["ifvalue"] ?? die("INVALIDIFVALUE");
	$thenid = $_POST["thenid"] ?? die("INVALIDTHENID");
	$thenvar = $_POST["thenvar"] ?? die("INVALIDTHENVAR");
	$thenvalue = $_POST["thenvalue"] ?? die("INVALIDTHENVALUE");
	$ifid = intval($ifid);
	$thenid = intval($thenid);
	$name = $_POST["name"] ?? "";
	$name = sanitizehtml($name);
	addcondition($ifid, $ifvar, $ifvalue, $thenid, $thenvar, $thenvalue, $name);
	header("DEBUG: conditions.php create condition successful");
	header("Location: conditions.php",true,303);
	die();
}

if ($action == "save") {
	$id = $_POST["id"] ?? die("INVALIDCONDITIONID");
	$ifid = $_POST["ifid"] ?? die("INVALIDIFID");
	$ifvar = $_POST["ifvar"] ?? die("INVALIDIFVAR");
	$ifvalue = $_POST["ifvalue"] ?? die("INVALIDIFVALUE");
	$thenid = $_POST["thenid"] ?? die("INVALIDTHENID");
	$thenvar = $_POST["thenvar"] ?? die("INVALIDTHENVAR");
	$thenvalue = $_POST["thenvalue"] ?? die("INVALIDTHENVALUE");
	$ifid = intval($ifid);
	$thenid = intval($thenid);
	$name = $_POST["name"] ?? "";
	$name = sanitizehtml($name);
	updatecondition($id, $ifid, $ifvar, $ifvalue, $thenid, $thenvar, $thenvalue, $name);
	header("DEBUG: conditions.php save condition successful");
	header("Location: conditions.php",true,303);
	die();
}

$editcondition = null;
$edit = false;
if ($action == "details") {
	$id = $_POST["id"] ?? die("INVALIDID");
	$editcondition = getconditionbyid($id);
	$edit = true;
}

//collect all variables sorted per device for selection in conditions
$variables = array();
foreach (getdevices() as $device) {
	$variables[$device["id"]] = array();
	foreach (getdata($device) as $datafieldname => $datafieldvalue) {
		array_push($variables[$device["id"]], $datafieldname);
	}
}
$variables = jsonencode($variables);

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
			
			
			<p id="variables" style="display: none;"><?php echo $variables; ?></p>
			<script>
				function getel(id) {return document.getElementById(id);}
				function rendervars(type) {
					let variables = JSON.parse(getel("variables").innerHTML)
					let select = getel(type + "var")
					select.innerHTML = "";
					variables[getel(type + "id").value].forEach(variable => select.innerHTML += "<option value=" + variable + ">" + variable + "</option>");
					select.removeAttribute("disabled");
				}
			</script>			
			
			<h3><?php echo $edit ? "Edit" : "Create";?> Condition</h3>
			<form method="post">
				<table>
					<tr>
						<td></td>
						<td>Device</td>
						<td>Variable</td>
						<td>Value</td>
					</tr>
					<tr>
						<td>IF</td>
						<td>
							<select name=ifid id=ifid onselect="rendervars('if')">
								<?php 
									foreach (getdevices() as $device) {
										echo "<option value=".$device["id"].">".getdevicename($device)."</option>";
									}
								?>
							</select>
						</td>
						<td>
							<select name=ifvar id=ifvar disabled onselect="getel('ifvalue').removeAttribute('disabled');">
						</td>
						<td>
							<input name=ifvalue id=ifvalue placeholder="Value" disabled>
						</td>
					</tr>
					<tr>
						<td>THEN</td>
						<td>
							<select name=thenid id=thenid onselect="rendervars('then')">
								<?php 
									foreach (getdevices() as $device) {
										echo "<option value=".$device["id"].">".getdevicename($device)."</option>";
									}
								?>
							</select>
						</td>
						<td>
							<select name=thenvar id=thenvar disabled onselect="getel('thenvalue').removeAttribute('disabled');">
						</td>
						<td>
							<input name=thenvalue id=thenvalue placeholder="Value" disabled>
						</td>
					</tr>
				</table>
				<?php 
					if ($edit) {
						?>
						<input type=text name=id value=<?php echo $editcondition["id"];?> style="display: none;">
						<?php 
					}
				?>
				<input type=text name=name placeholder="Name">
				<input type=text name=action value=<?php echo $edit ? "save" : "create";?> style="display: none;">
				<input type=submit value="<?php echo $edit ? "Save" : "Create";?> Condition">
			</form>
			
		</div>
	</body>
</html>
