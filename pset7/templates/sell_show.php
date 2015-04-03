<div class="col-md-6 col-md-offset-3">
	<h1>Congrats on selling <?= $sell["symbol"] ?> </h1>
	<p>Price per share: <?= "$". money_format('%i', $sell["price"]) ?> </p>
	<p>Number of shares: <?= $sell["number_of_shares"] ?> </p>
	<p>You received: <?= "$". money_format('%i', $sell["price"] * $sell["number_of_shares"]) ?> </p>
</div>
