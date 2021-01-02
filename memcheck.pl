#!/usr/bin/perl -w

my $cmd = "valgrind --tool=memcheck --leak-check=yes --log-file=shit --num-callers=200 ";
$cmd .= "--show-reachable=yes --track-fds=yes ";
$cmd .= "./infDraw";
`$cmd`;

