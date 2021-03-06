% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/MESS-package.R
\docType{data}
\name{smokehealth}
\alias{smokehealth}
\title{Effect of smoking on self reported health}
\format{A table with daily smoking categories for the rows and self reported health five years later as the columns.}
\source{
Data example found on the internet but originates from Svend Kreiner
}
\description{
Effect of smoking at 45 years of age on self reported health five years later. Data are on a sample of males from the Glostrup survey.
}
\examples{

data(smokehealth)
m <- smokehealth
m[,3] <- m[,3]+ m[,4]
m[4,] <- m[4,] + m[5,]
m <- m[1:4,1:3]
gkgamma(m)
chisq.test(m)

}
\keyword{datasets}
