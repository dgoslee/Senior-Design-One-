<!DOCTYPE html>
<html>
<head>
	<title>Fire Detection System Hub</title>
  <link rel="stylesheet" type ="text/css" href="css/layout.css">
  <style>
  @-webkit-keyframes blink {
    0% {
        opacity:1;
    }
    50% {
        opacity:0;
    }
    100% {
        opacity:1;
    }
}
@-moz-keyframes blink {
    0% {
        opacity:1;
    }
    50% {
        opacity:0;
    }
    100% {
        opacity:1;
    }
}
.objblink {
-webkit-transition: all 1s ease-in-out;
    -moz-transition: all 1s ease-in-out;
    -o-transition: all 1s ease-in-out;
    -ms-transition: all 1s ease-in-out;
    transition: all 1s ease-in-out;
    
    -webkit-animation-direction: normal;
    -webkit-animation-duration: 2s;
    -webkit-animation-iteration-count: infinite;
    -webkit-animation-name: blink;
    -webkit-animation-timing-function: ease-in-out;
    
-moz-animation-direction: normal;
    -moz-animation-duration: 2s;
    -moz-animation-iteration-count: infinite;
    -moz-animation-name: blink;
    -moz-animation-timing-function: ease-in-out;    
}
</style>

</head>
<body>
	<h1 id="title"> Fire Detection System Hub </h1>
<!--Menu for different pages of the site-->
	<header>
		<div class = "row">
		<ul class = "main-nav">
			<li class = "active"><a href="layout.php"> LAYOUT </a></li>
			<li><a href="about.php"> ABOUT </a></li>
			<li><a href="readings.php"> READINGS </a></li>


		</ul> 

		</div> 
	<div class = "Layout"> Layout </div>

	</header>
	<br>
<!--HTML prompt for user selecting their layout and entering where each device is-->
	<div class = "Floor"> Please select and upload your building layout </div>
<form method = "post" enctype = "multipart/form-data">
    <input type = "file" name = "image">
    <br>
    <input type = "submit" name = "submit" value = "submit">
</form>
<form>
    <div>How many devices do you have?</div>
    <input type="number" name="num1"/>
    <div><br><input type="submit" value="Enter"></div><br>
</form>
<!--Converts num1 so it can be used in php-->
<?php
$num1 = 0;
if (isset($_GET['num1'])) {
 
    $num1 = $_GET['num1'];
 
}
A[1] = 0;
if A[1] == 800 {
  myFunction();
}

?>
<!--Create multiple input fields based on value of num1-->
<!--$i increments starting at 1. Node.$i. becomes Node1, Node2, Node3...-->
<?php
echo "<form method = 'POST' action = 'layout.php?num1=$num1'>";
$rooms = array();
for ($i=1; $i<=$num1; $i++) {
    echo nl2br("Where is Node $i ?  \n");
    echo "<input type = 'text' name = 'room[]' class = 'class_name'/><br/>";
    echo '<div id="node'.$i.'">X</div>';
    echo nl2br(" \n");
}
echo "<input type = 'submit' value = 'SEND'/>";
echo "</form>";
?>
<!--Function to display each node ID and it's location-->
<?php
function location()
{
    $rooms = $_POST['room'];

  if (sizeof($rooms) > 0){  
    for($counter = 0; $counter < sizeof($rooms); $counter++)
    {
      echo "Node".($counter + 1).": ".$rooms[$counter]."<br />";
    }}
}
if(isset($_POST['room']))
{
  location();
}

?>
<a onclick="myFunction();" style="cursor: default; color: darkred;">Blink</a><br>

<!--Checking if file type is an image and saves to "images" table in database-->
<?php
if(isset($_POST['submit']))
{
  if (getimagesize($_FILES['image']['tmp_name'])==FALSE) {
      echo "failed";
  }
  else{
      $name=addslashes($_FILES['image']['name']);
      $image=base64_encode(file_get_contents(addslashes($_FILES['image']['tmp_name'])));
      saveimage($name,$image);
  }
}
//Function to connect to database: mysqli_connect(server, username, password, database)
function saveimage($name, $image){
    $con = mysqli_connect('us-cdbr-iron-east-02.cleardb.net', 'b9d264b004acd5', '65b3cf3c', 'heroku_553bb04cbc1909f');
    $sql="insert into images(name, image) values('$name', '$image')";
    $query = mysqli_query($con, $sql);
    if ($query) {
      echo "";
    }
    else{
      echo "";
    }
}
display();
//Function to display all images in the table
function display(){
    $con = mysqli_connect('us-cdbr-iron-east-02.cleardb.net', 'b9d264b004acd5', '65b3cf3c', 'heroku_553bb04cbc1909f');
    $sql = "select * from images";
    $query=mysqli_query($con,$sql);
    $num=mysqli_num_rows($query);
    for ($i=0; $i < $num; $i++){
      $result=mysqli_fetch_array($query);
      $img=$result['image'];
      echo '<img class ="img" src="data:image/jpeg;base64, '.$img.'"/>';
    }

}

?>
<script type="text/javascript">
//Set variables from php to new variables in javascript

var n1 = document.getElementById("node1");
var n2 = document.getElementById("node2");
var n3 = document.getElementById("node3");
var n4 = document.getElementById("node4");
var n5 = document.getElementById("node5");
var n6 = document.getElementById("node6");
var n7 = document.getElementById("node7");
var n8 = document.getElementById("node8");
var n9 = document.getElementById("node9");
var n10 = document.getElementById("node10");
var n11 = document.getElementById("node11");
var n12 = document.getElementById("node12");
var n13 = document.getElementById("node13");
var n14 = document.getElementById("node14");
var n15 = document.getElementById("node15");
var n16 = document.getElementById("node16");
var n17 = document.getElementById("node17");
var n18 = document.getElementById("node18");
var n19 = document.getElementById("node19");
var n20 = document.getElementById("node20");

//Selecting the icons when clicked on, moving the icon as the cursor is moving and placing the icon when the mouse is clicked again
var moving = false;

n1.addEventListener("mousedown", initialClick, false);
n2.addEventListener("mousedown", initialClick, false);
n3.addEventListener("mousedown", initialClick, false);
n4.addEventListener("mousedown", initialClick, false);
n5.addEventListener("mousedown", initialClick, false);
n6.addEventListener("mousedown", initialClick, false);
n7.addEventListener("mousedown", initialClick, false);
n8.addEventListener("mousedown", initialClick, false);
n9.addEventListener("mousedown", initialClick, false);
n10.addEventListener("mousedown", initialClick, false);
n11.addEventListener("mousedown", initialClick, false);
n12.addEventListener("mousedown", initialClick, false);
n13.addEventListener("mousedown", initialClick, false);
n14.addEventListener("mousedown", initialClick, false);
n15.addEventListener("mousedown", initialClick, false);
n16.addEventListener("mousedown", initialClick, false);
n17.addEventListener("mousedown", initialClick, false);
n18.addEventListener("mousedown", initialClick, false);
n19.addEventListener("mousedown", initialClick, false);
n20.addEventListener("mousedown", initialClick, false);


function myFunction(){
    n1.classList.toggle("objblink");
}


function move(e){
  var newX = e.clientX - 10;
  var newY = e.clientY - 10 + document.documentElement.scrollTop;

  image.style.left = newX + "px";
  image.style.top = newY + "px";
  
}

function initialClick(e) {

  if(moving){
    document.removeEventListener("mousemove", move);
    moving = !moving;
    return;
  }

  moving = !moving;
  image = this;

  document.addEventListener("mousemove", move, false);

}

</script>

</body>
</html>


