<?php include('server.php') ?>
<!DOCTYPE html>
<html>
<head>
  <title>Registration system PHP and MySQL</title>
  <link rel="stylesheet" type="text/css" href="css/register.css">
</head>
<body>
  <h1 id="title"> Fire Detection System Hub </h1> 
  <div class = "login-page">
  <div class = "form">
	 
  <form method="post" action="login.php">
  	<?php include('errors.php'); ?>
  	<div class="input-group">
  		<input type="text" placeholder="Username" name="username" >
  	</div>
  	<div class="input-group">
  		<input type="password" placeholder="Password" name="password">
  	</div>
  	<div class="input-group">
      <input type = "submit" value = "Login" name = "login_user" /> 
  	</div>
  	<p>
  		Not yet a member? <a href="index.php">Sign up</a>
  	</p>
    </div>
    </div>
  </form>
</body>
</html>