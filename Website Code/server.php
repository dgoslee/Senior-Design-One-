<?php
session_start();

// initializing variables
$username = "";
$email    = "";
$errors = array(); 

// connect to the heroku database mysqli_connect(server, username, password, database)
$db = mysqli_connect('us-cdbr-iron-east-02.cleardb.net', 'b9d264b004acd5', '65b3cf3c', 'heroku_553bb04cbc1909f');

// REGISTER USER
if (isset($_POST['reg_user'])) {
  // receive all input values from the form
  $username = mysqli_real_escape_string($db, $_POST['username']);
  $email = mysqli_real_escape_string($db, $_POST['email']);
  $password_1 = mysqli_real_escape_string($db, $_POST['password_1']);
  $password_2 = mysqli_real_escape_string($db, $_POST['password_2']);

  // form validation: ensure that the form is correctly filled ...
  // by adding (array_push()) corresponding error unto $errors array
  if (empty($username)) { array_push($errors, "USERNAME IS REQUIRED"); }
  if (empty($email)) { array_push($errors, "EMAIL IS REQUIRED"); }
  if (empty($password_1)) { array_push($errors, "PASSWORD IS REQUIRED"); }
  if ($password_1 != $password_2) {
  array_push($errors, "THE TWO PASSWORDS DO NOT MATCH");
  }

  // first check the database to make sure 
  // a user does not already exist with the same username and/or email
  $user_check_query = "SELECT * FROM users WHERE username='$username' OR email='$email' LIMIT 1";
  $result = mysqli_query($db, $user_check_query);
  $user = mysqli_fetch_assoc($result);
  
  if ($user) { // if user exists
    if ($user['username'] === $username) {
      array_push($errors, "USERNAME ALREADY EXISTS");
    }

    if ($user['email'] === $email) {
      array_push($errors, "EMAIL ALREADY EXISTS");
    }
  }

  // Finally, register user if there are no errors in the form
  if (count($errors) == 0) {
    $password = md5($password_1);//encrypt the password before saving in the database

    $query = "INSERT INTO users (username, email, password) 
          VALUES('$username', '$email', '$password')";
    mysqli_query($db, $query);
    $_SESSION['username'] = $username;
    $_SESSION['success'] = "You are now logged in";
    header('location: layout.php');
  }
}
if (isset($_POST['login_user'])) {
  $username = mysqli_real_escape_string($db, $_POST['username']);
  $password = mysqli_real_escape_string($db, $_POST['password']);

  if (empty($username)) {
    array_push($errors, "USERNAME IS REQUIRED");
  }
  if (empty($password)) {
    array_push($errors, "PASSWORD IS REQUIRED");
  }

  if (count($errors) == 0) {
    $password = md5($password);
    $query = "SELECT * FROM users WHERE username='$username' AND password='$password'";
    $results = mysqli_query($db, $query);
    if (mysqli_num_rows($results) == 1) {
      $_SESSION['username'] = $username;
      $_SESSION['success'] = "You are now logged in";
      header('location: layout.php');
    }else {
      array_push($errors, "USERNAME AND PASSWORD DO NOT MATCH");
    }
  }
}

?>