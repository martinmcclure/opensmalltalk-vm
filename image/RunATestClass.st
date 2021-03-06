"Run a single test class in a TestRunner.
 Usage: myvm myimage.image RunATestClass.st TheTestClass
 A confirmer will appear after the tests have run.  Click to exit or not."
| testRunner testClass |
testRunner := TestRunner open model.
testClass := Smalltalk getSystemAttribute: 3.
testRunner
	selectNoClasses;
	classAt: ((1 to: testRunner classList size) detect:
				[:i| (testRunner classList at: i) string endsWith: testClass])
	put: true;
	runAll.
(UIManager default confirm: 'Quit?') ifTrue:
	[[Smalltalk quit]
		on: MessageNotUnderstood
		do: [:ex| Smalltalk quitPrimitive]]
