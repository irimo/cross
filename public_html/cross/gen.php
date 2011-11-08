<?php
/**
* This program,the image changes BMP format by php:(
* Please use Imagemagick.
*/
require_once(DIRNAME(__FILE__)."/../../conf/conf.php");
require_once(CLASS_DIR."/common/function.imageBmp.php");
require_once(CLASS_DIR."/common/function.ImageCreateFromBmp.php");

//echo $_FILES['userfile']['type'];
list($w , $h) = getimagesize($_FILES['userfile']['tmp_name']);
if($w >= 1600 || $h >= 1200) die("shrink 1600*1200.");
if($w < 50 || $h < 50) die("spread 50*50.");

if(isset($_FILES['userfile'])){
	if($_FILES['userfile']['type'] == "image/pjpeg" ||
	 $_FILES['userfile']['type'] == "image/jpeg"){
		$image = imagecreatefromjpeg($_FILES['userfile']['tmp_name']);
	}elseif($_FILES['userfile']['type'] == "image/png" ||
	  $_FILES['userfile']['type'] == "image/x-png"){
		$image = imagecreatefrompng($_FILES['userfile']['tmp_name']);
	}elseif($_FILES['userfile']['type'] == "image/gif"){
		$image = imagecreatefromgif($_FILES['userfile']['tmp_name']);
	}elseif($_FILES['userfile']['type'] == "image/wbmp"){
		$image = imagecreatefromwbmp($_FILES['userfile']['tmp_name']);
	}elseif($_FILES['userfile']['type'] == "image/bmp"){
		$image = ImageCreateFromBMP($_FILES['userfile']['tmp_name']);
	} else{
		die("unsupported imagefileformat.");
	}
} else {
	die("select image.");
}

$date = date("ymdHis");
$before_filenaeme = "crs-{$date}.bmp";
$after_filenaeme = "crs-{$date}-2.bmp";
$jpg_imgname = "crs-{$date}.jpg";

imageBmp($image, TMP_IMG_DIR."/".$before_filenaeme);
$command = BIN_DIR."/cross/cross.exe ".TMP_IMG_DIR."/".$before_filenaeme." ".TMP_IMG_DIR."/".$after_filenaeme;
shell_exec($command);

$out_img = ImageCreateFromBMP(TMP_IMG_DIR."/".$after_filenaeme);
imagejpeg($out_img, TMP_IMG_DIR.'/'.$jpg_imgname);

print "<img src='".TMP_IMG_URL."/".$jpg_imgname."'>";