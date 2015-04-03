<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {

        // else render form
        render("add_funds.php", ["title" => "Add Funds"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["funds"]))
        {
            apologize("You must decide how much you want to add!");
        }
        if ($_POST["funds"] < 1 || !is_numeric($_POST["funds"]) )
        {
        	apologize("This is worthless! You must enter a number greater than 1!");
        }
        else 
        {
        	if (add_funds($_POST["funds"]) !== false)
        	{
        		// redirect user
   	 			redirect("/");
        	}
            // If quote was obtained, redirect_to show with the relevant information
            else
            {
                apologize("There was a problem!");
            }
        }
    }

?>