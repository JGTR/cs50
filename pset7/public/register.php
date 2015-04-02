<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }

        else if (empty($_POST["password_confirmation"]))
        {
            apologize("You must provide a password confirmation.");
        }

        else if($_POST["password"] != $_POST["password_confirmation"])
        {
            apologize("The password confirmation does not match the password you provided.");
        }

        // query database for user
        $rows = query("SELECT * FROM users WHERE username = ?", $_POST["username"]);

        // if we found user, check password
        if (count($rows) > 0)
        {
            apologize("That user already exists.");
        }
        else
        {   
            // Insert new record into DB
            if (query("INSERT INTO users (username, hash, cash) VALUES (?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"])) !== false)
            {
                // Get id for record just inserted into DB
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                $id = $rows[0]["id"];

                // Store id in session
                $_SESSION["id"] = $id;

                // redirect to portfolio
                redirect("index.php");

            }

            else
            {
                apologize("There was a problem with your registration.");
            }
        }
    }

?>