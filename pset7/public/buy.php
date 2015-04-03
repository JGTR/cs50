<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_new.php", ["title" => "Buy Shares"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a Symbol for the buy");
        }
        if (empty($_POST["number_of_shares"])) {
        	apologize("You must provide a number of shares for the buy");
        }
        else 
        {

            // If the form is complete, try to process the transaction
        	$buy = transact($_POST["symbol"], $_POST["number_of_shares"], 'buy');

        	if ( $buy !== false )
        	{
        		// Get id for record just inserted into DB
                $last_id = query("SELECT LAST_INSERT_ID() from transactions")[0]["LAST_INSERT_ID()"];
                // Retrieve right transaction record
                $buy = query("SELECT * FROM transactions WHERE id = ?", $last_id)[0];
        		render("buy_show.php", ["title" => "Your Buy", "buy" => $buy]);
        	} 
        	else
        	{
        		apologize("There was a problem with your request.");
        	}
        }
    }

?>