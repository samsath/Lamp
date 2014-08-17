<?php
	
	$f = new DOMDocument();
	$f = fopen("LampData.dat","w");
    
    	
	echo fwrite($f, $_POST["name"]."\n"); 
	echo fwrite($f, $_POST["dev"]."\n");
	echo fwrite($f, $_POST["YN"]."\n");
	echo fwrite($f, $_POST["Se"]."\n");
	echo fwrite($f, $_POST["Un"]."\n");
	echo fwrite($f, $_POST["Pwd"]."\n");
	echo fwrite($f, $_POST["Mac"]);
			
    	
    
	fclose($f);
?>

            
