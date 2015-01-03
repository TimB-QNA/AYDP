#!/usr/bin/php
This script reads a points file called "PCBOutline.txt"
and converts it to the required graphics calls for KiCAD's
PCB Editor. The filename, layer, y-ais inversion and line
width can all be changed by modifying variables at the top
of this script.
 
<?php
$fileName="PCBOutline.txt";
$layer="Edge.Cuts";
$invertY=true;
$width=0.2;

class point{
  public $x=0.0;
  public $y=0.0;
}

$datafile=file_get_contents($fileName);

$points=split("\n",$datafile);

$pointData=array();

foreach ($points as $pt){
  $ptData=split(" ",$pt);
  if (count($ptData)>=2){
    $tmpDat= new point();
//    print_r($ptData);
    $tmpDat->x=$ptData[0];
    $tmpDat->y=$ptData[1];
    $pointData[]=$tmpDat;
  }
}

for ($i=0;$i<count($pointData);$i++){
  if ($i<count($pointData)-1){
    $j=$i+1; // i.e. the line ends at the next point
  }else{
    $j=0;
  }
  $xi=$pointData[$i]->x;
  $yi=$pointData[$i]->y;
  $xj=$pointData[$j]->x;
  $yj=$pointData[$j]->y;
  if ($invertY){
    $yi=-$yi;
    $yj=-$yj;
  }
  print("(gr_line (start $xi $yi) (end $xj $yj) (angle 90) (layer $layer) (width $width))\n");
}

?>
