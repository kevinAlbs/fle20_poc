// Run mongocryptd with: --setParameter featureFlagFLE2=1
// Run this script with: mongosh --port 27020 fle2_to_mongocryptd.js

const testDb = db.getSiblingDB("admin");

const res = testDb.runCommand({
    insert: "db.test",
    documents: [{"foo": "bar"}],
    encryptionInformation: {
        type: 1,
        schema: {
            "db.test": {
                "escCollection": "db.test.esc",
                "eccCollection": "db.test.ecc",
                "ecocCollection": "db.test.ecoc",
                fields: [{path: "a", keyId: UUID(), bsonType: "string"}]
            }
        }
    }
});

printjson (res)

assert (res.hasOwnProperty("result"))

// Output with mongocryptd version 6.0.0-alpha-523-gb4cb11e
/*
{
  hasEncryptionPlaceholders: false,
  schemaRequiresEncryption: true,
  result: {
    insert: 'db.test',
    encryptionInformation: {
      type: 1,
      schema: {
        'db.test': {
          escCollection: 'db.test.esc',
          eccCollection: 'db.test.ecc',
          ecocCollection: 'db.test.ecoc',
          fields: [
            {
              path: 'a',
              keyId: UUID("ace57ba5-50db-4002-b50e-c360bec9614b"),
              bsonType: 'string'
            }
          ]
        }
      }
    },
    documents: [ { foo: 'bar' } ]
  },
  ok: 1
}
*/