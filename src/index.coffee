#
# Directly expose the exports from the C++ addon.
#
module.exports = require('bindings')('addon.node')
