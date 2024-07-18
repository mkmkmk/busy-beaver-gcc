# https://arxiv.org/pdf/0906.3749

n = 0
S = 0
while (n %% 3 != 2)
{
    n = if (n%%3 == 0) (5*n+18)/3 else (5*n+22)/3
    k = trunc(n/3)
    s = if (n%%3==0) (5*k^2+19*k+15) else if (n%%3==1) 5*k^2+25*k+27 else 6*k+12
    cat(sprintf("%10d %10d %10d %10d\n",S+16-1, k, n, s))
    S = S + s
}
