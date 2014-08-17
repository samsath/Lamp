<?php
$file = fopen("LampData.dat","r");
$fileEntrys = array();
while(! feof($file))
  {
  $fileEntrys[] = fgets($file);
  }

fclose($file);
print json_encode(array('Name' => $fileEntrys[0],
						'IP' => $fileEntrys[1],
						'Other' => $fileEntrys[2],
						'db' => $fileEntrys[3],
						'uname' => $fileEntrys[4],
						'pwd' => $fileEntrys[5],
						'MAC' => $fileEntrys[6]
						));
?> 
