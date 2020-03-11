<?php 
require_once("system.php");
if (!sessionvalid()) die("INVALIDSESSION");

$devices = getdevices();

function gettile($device) {
	//gettile: needs to output the data userfriendly for the GUI
	$data = getdata($device);
	$returnstring = "<table>";
	foreach ($data["data"] as $datafield => $datavalue) {
		$returnstring = $returnstring."<tr>";
		$returnstring = $returnstring."<td>".sanitizehtml($data["friendly"]["datavar"][$datafield] ?? $datafield)."</td>";
		$returnstring = $returnstring."<td>".sanitizehtml($data["friendly"]["datavalue"][$datafield] ?? $data["data"][$datafield] ?? "")."</td>";
		$returnstring = $returnstring."</tr>";
	}
	$returnstring = $returnstring."</table>";
	return $returnstring;
}

?>

<div class="tilegrid">
	
	<?php 
	foreach ($devices as $device) {
		?>
		<div class="tile">
			<h1><?php echo getdevicename($device);?></h1>
			<?php echo gettile($device); ?>
		</div>
		<?php
	}
	?>
	
</div>