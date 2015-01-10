fs = require 'fs'
path = require 'path'
{exec,spawn} = require 'child_process'
util = require 'util'

srcDir = 'src'
libDir = 'lib'
coffee = path.normalize("./node_modules/.bin/coffee")
jasmine = path.normalize("./node_modules/.bin/jasmine-node")
docco = path.normalize("./node_modules/.bin/docco")

task 'watch', 'Watch source files and build changes', ->
  watch = spawn coffee, ['-cw', '--no-header', '-o', libDir, srcDir]
  watch.stdout.on 'data', (data) -> console.log data.toString().trim()

task 'build', 'Compile all CoffeeScript files', ->
  # prepare lib directory
  if not fs.existsSync libDir
    fs.mkdirSync libDir

  # run coffee-script compile
  exec "#{coffee} -c --no-header -o #{libDir} #{srcDir}", (err, stdout, stderr) ->
    if err
      util.log err
      process.exit 1 # abort npm packaging
    util.log "Compiled CoffeeScript."

task 'test', 'Run the Jasmine tests', ->
  exec "#{jasmine} --color --coffee --verbose spec/", (err, stdout, stderr) ->
    if err
      util.log "Testing Failed - \n#{stdout}"
      process.exit 1 # abort npm packaging
    util.log("Test Results - \n#{stdout}")

task 'doc', 'Generate documentation', ->
  exec "#{docco} src/*", (err, stdout, stderr) ->
    if err
      util.log "Docco Failed - \n#{stdout}"
      process.exit 1 # abort npm packaging
    util.log("Docco generated documentation - \n#{stdout}")
