<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
    	$transactions = query("SELECT * FROM transactions WHERE user_id = ?", user_id());

        // else render form
        render("history.php", ["title" => "Your History", "transactions" => $transactions]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
    	// Post to this route is not valid
    	apologize("Post to this route is not valid.");
    }

?>