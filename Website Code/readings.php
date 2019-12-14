<!DOCTYPE html>
<html>
<head>
	<title>Fire Detection System Hub</title>
	<link rel="stylesheet" type="text/css" href="css/readings.css">
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
	<header>
		<div class = "row">
		<ul class = "main-nav">
			<li><a href="layout.php"> LAYOUT </a></li>
			<li><a href="about.php"> ABOUT </a></li>
			<li class ="active"><a href="readings.php"> READINGS </a></li>

		</ul> 

		</div> 

	</header>
	<div class = "Readings"> Readings </div>
	<a href=\\"http://www.169.254.239.112/cgi-bin/console.cgi">Sensor Readings</a>
	<br>
	<a onclick="myFunction();"style="cursor: default; color: darkred;"> TESTING </a>
	<h2 class = "MotionSensor"> Motion Sensing... </h2>
	<a id = "motion" class = "Detected"> MOTION DETECTED !! </a>

</body>
</html>
<script type="text/javascript">
	function myFunction(){
		var move = document.getElementById("motion");
    	if(move.style.visibility == "hidden") {
    		move.style.visibility = "visible";
    		move.classList.toggle("objblink");
    		


    } 	else if(move.style.visibility = "visible") {
    		move.style.visibility = "hidden";
    }
	}
</script>