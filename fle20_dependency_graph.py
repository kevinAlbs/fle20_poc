import graphviz # doctest: +NO_EXE

dot = graphviz.Digraph(graph_attr={"rankdir": "LR"})
# Here is a proposed list of MONGOCRYPT tickets. Parenthesized comments come from the complexity estimate.

# (Support AES block cipher with CTR mode.)
dot.node("M1", "AES CTR - Windows")
dot.node("M2", "AES CTR - macOS")
dot.node("M3", "AES CTR - OpenSSL")
dot.node("M4", "AES CTR callback")
# (Add optional AES block cipher with ECB mode cryptography callback for .NET. libmongocrypt will use the result to produce CTR. See Q2: Do all drivers support CTR cipher block mode?)
dot.node("M5", "AES ECB callback")
# (Support processing and generation of new payloads.)
dot.node("M6", "Gen all tokens") # Generate all FLE 2.0 tokens from DEK.
dot.edge("M3", "M6") # Need at least OpenSSL to generate tokens.
# (For encryption: Process Payload Type 3. Generate Payload Type 4, 5, and 6.)
# (For decryption: Process Payload Type 4, 5, 6, and 7. Generate plaintext.)
dot.node("M7", "Process new Payload Types")
dot.edge("M6", "M7") # Depends on tokens.
# (Support processing FLE 2.0 commands.)
# (Append "encryptionInformation" to outgoing commands if the collection is present in the EncryptedFieldConfigMap. See Walkthrough Insert.)
dot.node("M8", "Support EncryptedFieldConfigMap")
dot.node("M9", "Support find and insert")
dot.edge("M8", "M9")
dot.edge("M7", "M9")
# (Support processing delete command in libmongocrypt.)
# (libmongocrypt appends the field "encryptionInformation.tokens" to the "delete" command. See Walkthrough Delete.)
dot.node("M10", "Support delete")
dot.edge("M8", "M10")
dot.edge("M7", "M10")
# (Add new context to support ClientEncryption.Compact.)
dot.node("M11", "Support Compact context")
dot.edge("M6", "M11") # Only need tokens.
# (Add new context to support ClientEncryption.GenerateEquality.)
dot.node("M12", "Support GenerateEquality context")
dot.edge("M7", "M11") # Need to process Payload 3 to Payload 5.
# (Support bypassQueryAnalysis option.)
dot.node("M13", "Support bypassQueryAnalysis option")
# (Error for Explicit Encryptions with the following:)
# (EncryptOpts.algorithm and EncryptOpts.indexType are both set.)
# (EncryptOpts.contentionFactor is set but indexType is not Equality.)
dot.node("M14", "Support explicit enc/dec")
dot.edge("M7", "M14") # Need to process payload type 3.

dot.render('fle20_dependency.gv', view=True)