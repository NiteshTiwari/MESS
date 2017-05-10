// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
// #include <add-ons/sample.h>
// #include <RcppArmadilloExtensions/sample.h>
using namespace Rcpp;


// Compute ks test statistic with no correction
// Assumes two-sided
double ksteststatistic(arma::colvec x) {
  arma::uword k=x.n_elem;
  arma::uword n=arma::accu(x);
  arma::colvec b = arma::linspace(double(n)/double(k), n, k);
  arma::colvec b2 = arma::linspace(0.0, double(n)*double(k-1)/double(k), k); 

  return(  std::max(arma::max(arma::abs(arma::cumsum(x) - b)),
	       arma::max(arma::abs(arma::cumsum(x) - b2))
	       )
	   );
}


//' Kolmogorov-Smirnov goodness of fit test for cumulative discrete data
//'
//' The name of the function might change in the future so keep that in mind!
//'
//' @description Kolmogorov-Smirnov goodness of fit test for cumulative discrete data. 
//' @param x A vector representing the contingency table.
//' @param B The number of simulations used to compute the p-value.
//' @param prob A positive vector of the same length as x representing the distribution under the null hypothesis. It will be scaled to sum to 1. If NULL (the default) then a uniform distribution is assumed.
//' @details Simulation is done by random sampling from the null hypothesis.
//' @return A list of class "htest" giving the simulation results.
//' @author Claus Ekstrom <claus@@rprimer.dk>
//' @examples
//'
//' x <- 1:6
//' kstest(x)
//'
//' @export
// [[Rcpp::export]]
List kstest(NumericVector x, int B=10000, Rcpp::Nullable<Rcpp::NumericVector> prob=R_NilValue) {

  arma::colvec X(x.begin(), x.length(), false);

  // Sanity checks
  if (B<1)
    Rcpp::stop("The number of permutation must be greater than 0");

  arma::uword N = sum(X);
  arma::uword K = X.n_elem;

  NumericVector PP( K );
  // Compute column probabilities under H0
  if (prob.isNotNull()) {
    PP = clone(prob);
    
    if (PP.size() != x.size()) {
      Rcpp::stop("The lengths of x and prob must match");
    }    
	
    double probsum = 0;
    // Check if any element is non-negative
    for(int i = 0; i < K; i++) {
      probsum += PP(i);
      if (PP(i) <= 0 )
	Rcpp::stop("The probabilities under H0 must be positive");
    }
    for(int i = 0; i < K; i++) {
      //      PP(i) /= probsum;
    }

  } else {
    // NULL - set uniform distribution
    for(int i = 0; i < K; i++) {
      PP(i) = 1.0/double(K);
    }
  }

  IntegerVector frame = seq_len(K);  // Sampling set

  double originalks = ksteststatistic(X);

  arma::colvec testtable(K);

  int larger=0;

  for (int i=0; i<B; i++) {
    // Empty the simulated vector
    testtable.zeros();

    IntegerVector res = sample( frame, N, TRUE, PP );
    
      //    IntegerVector res = RcppArmadillo::sample(frame, N, TRUE, PP) ;

    for (int k = 0; k < N; k++) {
      testtable(res(k)-1) +=1;
    }

    if (ksteststatistic(testtable) >= originalks)
      larger +=1;

  }
  
  NumericVector statistic = NumericVector::create(_["KS-statistic"] = originalks) ;

  Rcpp::List RVAL =  Rcpp::List::create(Rcpp::Named("method") = "Kolmogorov-Smirnov discrete cumulative goodness-of-fit test",
					Rcpp::Named("statistic") = statistic,
					Rcpp::Named("p.value") = (1+larger)/(B+1.0));

  RVAL.attr("class") = "htest";
  
  return(RVAL);
  
}

