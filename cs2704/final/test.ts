import { clustersDbscan, Feature, Point, point, FeatureCollection, featureCollection } from "@turf/turf"

const features: Array<Feature<Point>> = [];

features.push(point("" as any))

clustersDbscan(featureCollection(features), 0.83)