#!perl -w
use strict;
# Little script to convert a regular XBM to TiLDA MKe bitmap
# only tested with fullscreen bitmaps!
# Hot file handle magic...
select((select(STDERR), $| = 1)[0]);
select((select(STDOUT), $| = 1)[0]);
sub t(@);
sub d($);
sub chug($);
my $f = shift;
#~ $f = 'blankish.xbm' if not $f;
if(not defined $f or not $f =~ /^(.*)\.xbm$/i){
    die "Usage: gimme an XBM file dude!\n";
}
my $name = $1;
t "Reading file '$f'...";
my $data = chug($f);
t "OK";
my @lines = split /^/, $data;
@lines = grep{chomp; s/^\s+//; s/\s+$//; length;} @lines;
#~ t d \@lines;
my($width, $height) = (0,0);
my @head = @lines[0..5];
foreach(@head){
    if(/_width\s+(\d+)/){$width = $1;}
    if(/_height\s+(\d+)/){$height = $1;}
}
t "width x height = $width x $height";
my @k;
foreach(@lines){ push @k, split /,/; }
@k = grep { s/^.*(0x[0-9A-Fa-f]{1,2}).*$/$1/o; /(0x[0-9A-Fa-f]{1,2})/o } @k;
#~ t d \@k;
my $bc = scalar(@k);
t "Pulled out $bc hex bytes";
if($bc != $width * $height / 8) {
    die "byte count $bc does not match that expected for w x h";
}
t "OK - reorder bytes for MKe bitmap";
my $wb = int($width/8) + (($width & 0x07) ? 1: 0);
t "width in whole bytes for $width pixels = $wb";
my @mke;
for(my $col = 0; $col < $wb; $col++){
    for(my $row = $height - 1; $row >= 0; $row--){
        my $idx = ($row * $wb) + $col;
        my $val = $k[$idx];
        #~ t "Column $col + Row $row = idx $idx = $val";
        push @mke, $val;
    }
}
my $out = "static const uint8_t ".uc($name)."_BM[] = {\n"
	."    $width, // width\n"
	."    $height , // height\n";
#~ $out .= join(", ", @mke);
while(scalar @mke){
	$out .= join(", ", splice(@mke, 0, 16)).",\n";
}
$out .= "};\n";
# meh, just print it out
t $out;

sub t(@) {
    foreach (@_) {
       print STDOUT "$_\n";
    }
}
sub d($) {
    require Data::Dumper;
    my $s = $_[0];
    my $d = Data::Dumper::Dumper($s);
    $d =~ s/^\$VAR1 =\s*//;
    $d =~ s/;$//;
    chomp $d;
    return $d;
}
sub chug($) {
  my $filename = shift;
  local *F;
  open F, "< $filename" or die "Couldn't open `$filename': $!";
  local $/ = undef;
  return <F>;
}  # F automatically closed

