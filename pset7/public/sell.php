<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("sell_new.php", ["title" => "Sell Shares"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a Symbol for the sell");
        }
        if (empty($_POST["number_of_shares"])) {
        	apologize("You must provide a number of shares for the sell");
        }
        else 
        {

            // If the form is complete, try to process the transaction
        	$sell = transact($_POST["symbol"], $_POST["number_of_shares"], 'sell');

        	if ( $sell !== false )
        	{
        		// Get id for record just inserted into DB
                $last_id = query("SELECT LAST_INSERT_ID() from transactions")[0]["LAST_INSERT_ID()"];
                // Retrieve right transaction record
                $sell = query("SELECT * FROM transactions WHERE id = ?", $last_id)[0];
        		render("sell_show.php", ["title" => "Your Sell", "sell" => $sell]);
        	} 
        	else
        	{
        		apologize("There was a problem with your request.");
        	}
        }
    }

?>