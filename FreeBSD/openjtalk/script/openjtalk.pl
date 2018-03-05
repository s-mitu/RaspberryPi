#!/usr/local/bin/perl
use strict;
use warnings;
use Time::Local;
use File::Sync qw(fsync sync);

my $path = "/usr/local";
my $audioplayer = "/usr/local/bin/play ";
my $hontai = $path."/bin/open_jtalk";
my $m_voice = $path.'/share/hts_voice/hts_voice_nitech_jp_atr503_m001-1.05/nitech_jp_atr503_m001.htsvoice';
my $f_voice = $path.'/share/hts_voice/mei_normal.htsvoice';
my $h_voice = $path.'/share/hts_voice/mei_happy.htsvoice';
my $a_voice = $path.'/share/hts_voice/mei_angry.htsvoice';
my $s_voice = $path.'/share/hts_voice/mei_sad.htsvoice';
my $b_voice = $path.'/share/hts_voice/mei_bashful.htsvoice';
my $voice = $m_voice;
my $sex = "M";
my $dic   = $path.'/share/open_jtalk/open_jtalk_dic_utf_8-1.08';
my $tmpdir = "/tmp";
my $infile = "$tmpdir/in.txt";
my $outfile = "$tmpdir/out.wav";
my $talk = "";
my @opts;

foreach(@ARGV){
  $talk = $_;
  if($talk =~ /^(M|F|N|H|A|B|S):/){
    $sex = $1;
    $talk =~ s/^(M|F|N|H|A|B|S)://;
  }
  if($sex eq "F" || $sex eq "N"){
    $voice = $f_voice;
  } elsif ($sex eq "H") {
    $voice = $h_voice;
  } elsif ($sex eq "A") {
    $voice = $a_voice;
  } elsif ($sex eq "B") {
    $voice = $a_voice;
  } elsif ($sex eq "S") {
    $voice = $s_voice;
  }
  open(OUT,">$infile");
    print OUT "$talk";
  close(OUT);

  if($sex eq "F"){
    @opts = (
            -x  => "$dic",
            -ow => "$outfile",
            -a  => 0.075, # 高低？
            -u  => 0.0, # 有声化・無声化？
            -jm => 0.5, # 大小？
            -jf => 1.2, # 抑揚？
	    -m  =>  "$voice"
           );
  }else{
    @opts = (
            -x  => "$dic",
            -ow => "$outfile",
	    -m  =>  "$voice"
           );
  }
  sync();
  my $param = $hontai." ".join(" ",@opts)." $infile";
  system($param);
  sync();
  system("$audioplayer $outfile");
  sync();
  unlink($infile,$outfile);
}
exit;

