{
  "targets": [
    {
      "target_name": "lzh",
      "sources": [ "src/binding.cc", "src/lzh.c" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "<!(node -e \"require('cpp-debug')\")"
      ]
    }
  ]
}
