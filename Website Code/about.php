<!DOCTYPE html>                                            								
<html>																					
<head>																					
	<title>Fire Detection System Hub</title>                                            
	<link rel="stylesheet" type="text/css" href="css/about.css">                        
</head>																					
<body>																					
	<h1 id="title"> Fire Detection System Hub </h1>										
	<header>
		<div class = "row">	
		<!--Creates classes for the list of links to different sections of the webpage. Connects each link to the corresponding webpage. "Active" is the page that is currently open-->															
		<ul class = "main-nav">
			<li><a href="layout.php"> LAYOUT </a></li>
			<li class = "active"> <a href="about.php"> ABOUT </a></li>
			<li><a href="readings.php"> READINGS </a></li> 


		</ul> 

		</div> 

	</header>
	<!-- Labels the page. Identifies which tab the user is currently in -->
	<div class = "About"> About </div>	

	<!-- Inserts an image -->
	<div id = "system"> 
	<img src="IMG_1077.jpg" width="500" length = "250">								
	</div>

	<!-- Basic information about the system-->
	<div class = "Info"> 
	WHO?<br>												
		This system was developed by University of Maryland Eastern Shore seniors David Goslee, Dedrick McCoy and Israel Akinsoyinu.<br> 
		WHAT?<br> 
		This is a fire detection system that notifies the building occupants and first responders of where a fire is in the building.<br>
		HOW?<br> 
		Fire is detected by carbon monoxide, temperature and ionization sensors. Occupants are notified via SMS and 911 is dialed, both done using a raspberry pi phone.<br> 
		WHERE?<br> 
		This detector is intended for larger buildings with multiple floors and rooms. These buildings include, (but not limited to) schools, hospitals and corporate offices. Although it is meant for bigger establishments, this system can also be used for smaller buildings such as homes.<br> 
		WHY?<br> 
		The objective of this system is to have multiple ways to detect a flame and have the ability to alert occupants and responders of exactly where in the building the flame is.<br>  
		WHEN?<br> 
		This system was developed, programmed and constructed in 2019. 
	</div>

</body>
</html>