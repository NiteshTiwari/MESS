% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/MESS-package.R
\docType{data}
\name{qpcr}
\alias{qpcr}
\title{Gene expression from real-time quantitative PCR}
\format{A data frame with 630 observations on the following 4 variables.
\tabular{lll}{ \code{flour} \tab numeric \tab Fluorescence level\cr
\code{line} \tab factor \tab Plant lines \code{rnt} (mutant) and \code{wt}
(wildtype)\cr \code{cycle} \tab numeric \tab Cycle number for the
experiment\cr \code{transcript}\tab factor \tab Transcript used for the
different runs\cr }}
\source{
Data provided by Kirsten Jorgensen <kij@life.ku.dk>. \cr Added by Claus Ekstrom <ekstrom@life.ku.dk>
}
\description{
Gene expression levels from real-time quantitative polymerase chain reaction
(qPCR) experiments on two different plant lines. Each line was used for 7
experiments each with 45 cycles.
}
\examples{

data(qpcr)

#
# Analyze a single run for the wt line, transcript 1
#
run1 <- subset(qpcr, transcript==1 & line=="wt")

model <- nls(flour ~ fmax/(1+exp(-(cycle-c)/b))+fb,
             start=list(c=25, b=1, fmax=100, fb=0), data=run1)

print(model)

plot(run1$cycle, run1$flour, xlab="Cycle", ylab="Fluorescence")
lines(run1$cycle, predict(model))

}
\references{
Morant, M. et al. (2010). Metabolomic, Transcriptional, Hormonal
and Signaling Cross-Talk in Superroot2. \emph{Molecular Plant}. 3,
p.192--211.
}
\keyword{datasets}
