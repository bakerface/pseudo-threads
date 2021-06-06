build = ARGUMENTS.get('--build', 'test')

SConscript('SConscript.' + build,
  variant_dir='.build/' + build,
  duplicate=0,
  exports=[ 'build' ])
