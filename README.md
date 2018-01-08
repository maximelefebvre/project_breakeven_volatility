# project_breakeven_volatility

This project as been done in the context of the C++ class given by Johan Mabille and Sylvain Corlay in M2 Financial Markets at University Paris Dauphine.

## Collaborators

Louis Le Pas de Sécheval - Student in M2 Financial Markets (promotion 2018), University Paris Dauphine
Maxime Lefebvre - Student in M2 Financial Markets (promotion 2018), University Paris Dauphine

## Idea of the project

The main purpose of this algorithm was to code a program allowing us to find the **Breakeven Volatility** implied by the evolutions of the spot price.
This basically means finding the implied volatility that cancels the PnL of the hedge portfolio linked to a short option (in our case, a European Call Option).

## What we did

We created a class corresponding to an Option, taking as data members the type of option and the different parameters in the pattern of the Black-Scholes model.
From this class, we were able to compute the price, delta and cash positions relatively to the spot price and the different parameters.
This allowed us to create a PnL vector, evolving at each step depending on the position on the underlying or the cash.

As it has been said before, we want the volatility that cancels the PnL. That is why we worked by dichotomy for finding this volatility.

This method allows us to get a **Volatility Smile** for different Strike prices over a period of one year.

## Potential enhancements

We integrated a class for managing the dates as objects, as it has been done with the library datetime in Python for example.
We did not full integrated this component in the code because of lack of time. In effect, the objective was to leveradge this component in order to give a window on which computing the **Volatility Smile**.
In order to compensate this, we had to code a short script in Python, doing the work on the csv file using Pandas and Datetime library.
