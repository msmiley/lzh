#
# Jasmine Test Spec for npm-template-cpp
#
describe "C++ Template Addon", ->
  addon = require '../'

  it "should uppercase a string", ->
    expect(addon.toUpper("qwerty")).toEqual "QWERTY"
