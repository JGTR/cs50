<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_new.php", ["title" => "Get Quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a Symbol for the quote.");
        }
        else 
        {
            // Get quote
            $quote = lookup($_POST["symbol"]);

            // Apologize if quote was not obtained
            if ($quote == false)
            {
                apologize("That symbol does not appear to be a real company, or is not found in Yahoo finance.");
            }

            // If quote was obtained, redirect_to show with the relevant information
            else
            {
                render("quote_show.php", ["title" => "Your Quote", "quote" => $quote]);
            }
        }
    }

?>