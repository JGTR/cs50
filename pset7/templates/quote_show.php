<div class="col-md-6 col-md-offset-3">
	<h1>Your Quote for <?= $quote["symbol"] ?> </h1>
		<p>Name: <?= $quote["name"] ?> </p>
		<p>Price per share: <?= "$" . money_format('%i', $quote["price"]) ?> </p>
</div>
