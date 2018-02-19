Write a C++ program to price a European-style option using each of the methods described below; the option price style (call, barrier is up and out) and computational method are user-defined. For the program output test, assume that the stock price process is geometric Brownian motion with volatility s = 0.3, initial asset price S(0) = 100, constant risk-free interest rate r = 0.05, dividend yield d = 0.02, option type call, strike K = 110, out barrier U = 120, and maturity T = 1 year; for the Monte Carlo simulations, use J = 10000 paths, I = 252 time steps, and the Euler method of solution of dS(t) = S(t)((r - d) dt + s dW(t)) to generate geometric
Brownian motion sample paths, unless specified otherwise. When using control variates, choose J1 = 1000 as the number of pilot simulations used to estimate the optimal control coefficient, b*, and J2 = 9000 as the number of pricing simulations used to estimate the desired option price.

See section 7.3.1 in Shreve for a discussion of the up-and-out barrier option and Equations
(7.3.19) or (7.3.20) for a closed-form formula for the price of an up-and-out barrier call option.

(a) Use the closed-form formula to compute the price for a European-style call option with
an up-and-out barrier. 

(b) Use Monte Carlo simulation to compute the prices for a European-style call with an upand-
out barrier, the standard error, and the computation time.

(c) Use Monte Carlo simulation with antithetic variance reduction to compute the prices for a
European-style call with an up-and-out barrier, the standard error, and the computation
time.

(d) Use Monte Carlo simulation with vanilla option control variates (with the same strikes)
to compute the prices for a European-style call with an up-and-out barrier, the standard
error, and the computation time.
